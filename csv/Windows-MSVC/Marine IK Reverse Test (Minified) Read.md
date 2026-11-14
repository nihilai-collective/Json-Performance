
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 562.304 | 0.224577 | 9505.68ms | 1834197 | 40 | 1.95226e+09 | 3.11082e+06 | 0.952823 | 5.40417 | 1(Win) | true |
| Jsonifier | 459.478 | 0.270862 | 5746.34ms | 1834197 | 80 | 8.50645e+09 | 3.80699e+06 | 0.386569 | 6.61441 | 2(Loss) | true |
| Glaze | 318.825 | 0.334171 | 8253.8ms | 1834197 | 40 | 1.34458e+10 | 5.48648e+06 | 0.241132 | 9.53298 | 3(Loss) | true |
| simdjson (ondemand) | 196.982 | 0.241064 | 6232.46ms | 1834197 | 40 | 1.833e+10 | 8.88012e+06 | 0.0945043 | 15.4287 | 4(Loss) | true |
