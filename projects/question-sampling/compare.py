"""Compare two question selection strategies across repeated papers."""

import random
import statistics

BANK_SIZE = 100
QUESTIONS_PER_PAPER = 20
PAPERS = 10
SEEDS = range(30)


def run(seed, balanced):
    rng = random.Random(seed)
    bank = range(BANK_SIZE)
    counts = [0] * BANK_SIZE
    previous = None
    adjacent_overlaps = []
    for _ in range(PAPERS):
        if balanced:
            # Randomly break ties among questions with equal exposure.
            candidates = list(bank)
            rng.shuffle(candidates)
            candidates.sort(key=counts.__getitem__)
            paper = candidates[:QUESTIONS_PER_PAPER]
        else:
            paper = rng.sample(bank, QUESTIONS_PER_PAPER)

        current = set(paper)
        if len(current) != QUESTIONS_PER_PAPER:
            raise RuntimeError("A paper must contain 20 distinct questions.")
        if previous is not None:
            adjacent_overlaps.append(len(current & previous))
        previous = current
        for question in paper:
            counts[question] += 1
    if balanced and counts != [2] * BANK_SIZE:
        raise RuntimeError("Every question should appear twice in the balanced experiment.")
    return sum(count > 0 for count in counts), statistics.mean(adjacent_overlaps), max(counts) - min(counts)


def main():
    print("strategy,mean_coverage_pct,mean_adjacent_repeats,mean_exposure_range")
    for name, balanced in (("independent", False), ("balanced", True)):
        rows = [run(seed, balanced) for seed in SEEDS]
        coverage, overlap, spread = (statistics.mean(column) for column in zip(*rows))
        print(f"{name},{coverage / BANK_SIZE * 100:.2f},{overlap:.2f},{spread:.2f}")


if __name__ == "__main__":
    main()
