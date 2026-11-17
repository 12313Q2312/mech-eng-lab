import json
import pathlib
import subprocess
import sys
import tempfile
import unittest

ROOT = pathlib.Path(__file__).resolve().parents[1]
CLI_PATH = ROOT / 'bin' / 'researchos'


class CLI(unittest.TestCase):
    def invoke(self, *args):
        return subprocess.run([sys.executable, str(CLI_PATH), *map(str, args)], capture_output=True, text=True)

    def test_doctor_json(self):
        p = self.invoke('doctor', '--json')
        self.assertEqual(p.returncode, 0, p.stderr)
        info = json.loads(p.stdout)
        self.assertIn('kernel', info)
        self.assertNotIn('username', info)
        self.assertNotIn('hostname', info)

    def test_init_and_run(self):
        with tempfile.TemporaryDirectory() as t:
            p = self.invoke('init', 'demo_lab', '--parent', t)
            self.assertEqual(p.returncode, 0, p.stderr)
            project = pathlib.Path(t) / 'demo_lab'
            self.assertTrue((project / 'researchos-project.json').exists())
            r = self.invoke('run', project, '--', sys.executable, 'experiments/hello.py')
            self.assertEqual(r.returncode, 0, r.stderr)
            records = list((project / 'runs').glob('*.json'))
            self.assertEqual(len(records), 1)
            meta = json.loads(records[0].read_text())
            self.assertEqual(meta['exit_code'], 0)
            self.assertEqual(meta['status'], 'completed')
            self.assertIn('elapsed_seconds', meta)
            self.assertTrue((project / 'runs' / meta['stdout_file']).is_file())

    def test_no_overwrite_and_bad_name(self):
        with tempfile.TemporaryDirectory() as t:
            self.assertNotEqual(self.invoke('init', '../wrong', '--parent', t).returncode, 0)
            self.assertEqual(self.invoke('init', 'demo', '--parent', t).returncode, 0)
            self.assertNotEqual(self.invoke('init', 'demo', '--parent', t).returncode, 0)

    def test_failed_experiment_still_records_evidence(self):
        with tempfile.TemporaryDirectory() as t:
            self.assertEqual(self.invoke('init', 'demo', '--parent', t).returncode, 0)
            project = pathlib.Path(t) / 'demo'
            p = self.invoke('run', project, '--', sys.executable, '-c', 'import sys; sys.exit(7)')
            self.assertEqual(p.returncode, 7)
            data = json.loads(next((project / 'runs').glob('*.json')).read_text())
            self.assertEqual(data['exit_code'], 7)

    def test_timeout(self):
        with tempfile.TemporaryDirectory() as t:
            self.assertEqual(self.invoke('init', 'demo', '--parent', t).returncode, 0)
            project = pathlib.Path(t) / 'demo'
            p = self.invoke('run', '--timeout', '0.1', project, '--', sys.executable, '-c', 'import time; time.sleep(2)')
            self.assertEqual(p.returncode, 124, p.stderr)
            data = json.loads(next((project / 'runs').glob('*.json')).read_text())
            self.assertEqual(data['status'], 'timeout')


if __name__ == '__main__':
    unittest.main()
