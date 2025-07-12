import os
import sys

# Add parent directory to sys.path so we can import DatasetGenerator
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
from dataset_gen import DatasetGenerator

# Required features for model prediction
REQUIRED_FEATURES = [
    'add', 'mul', 'load', 'store', 'call',
    'define', 'br i1', 'loops', 'basic_blocks', 'total_instructions'
]

def extract_features_from_c_file(c_file_path):
    generator = DatasetGenerator()
    feats = generator.extract_features(c_file_path)

    # Ensure all required features are present (fill missing with 0)
    features_complete = {key: feats.get(key, 0) for key in REQUIRED_FEATURES}
    return features_complete
