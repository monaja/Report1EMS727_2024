% Create a new Simulink model
model = 'sine_wave_with_noise';
open_system(new_system(model));

% Add a Sine Wave block
add_block('simulink/Sources/Sine Wave', [model, '/Sine Wave'], ...
    'Position', [100, 100, 150, 130]);

% Add a Random Number block to simulate noise
add_block('simulink/Sources/Random Number', [model, '/Noise'], ...
    'Position', [100, 200, 150, 230]);

% Add a Sum block to add noise to the sine wave
add_block('simulink/Math Operations/Sum', [model, '/Sum'], ...
    'Position', [250, 150, 300, 180], ...
    'Inputs', '|+-');

% Add a Transfer Function block to cancel the noise
add_block('simulink/Continuous/Transfer Fcn', [model, '/Transfer Fcn'], ...
    'Position', [400, 150, 450, 180], ...
    'Numerator', '[1]', ...
    'Denominator', '[1 1]');

% Add a Scope block to visualize the output
add_block('simulink/Sinks/Scope', [model, '/Scope'], ...
    'Position', [550, 150, 600, 180]);

% Connect the blocks
add_line(model, 'Sine Wave/1', 'Sum/1');
add_line(model, 'Noise/1', 'Sum/2');
add_line(model, 'Sum/1', 'Transfer Fcn/1');
add_line(model, 'Transfer Fcn/1', 'Scope/1');

% Save and open the model
save_system(model);
open_system(model);