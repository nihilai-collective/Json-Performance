
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2407.28 | 0.444949 | 4591.48ms | 108313 | 640 | 2.33297e+07 | 42909.6 | 0.78797 | 1(Win) | true |
| Glaze | 1465.71 | 0.144083 | 7169.84ms | 108313 | 640 | 6.59897e+06 | 70474.8 | 0.0880522 | 2(Loss) | true |
| Jsonifier (two-stage) | 1397.76 | 0.206474 | 7356.89ms | 108313 | 2560 | 5.96029e+07 | 73900.8 | 0.719338 | 3(Loss) | true |
| simdjson (ondemand) | 1113.71 | 0.693439 | 9605.9ms | 108313 | 40 | 1.6546e+07 | 92748.8 | 0.202821 | 4(Loss) | true |
| simdjson (reflection) | 1085.7 | 0.44557 | 5028.68ms | 108313 | 640 | 1.15015e+08 | 95141.6 | 1.50646 | 5(Loss) | true |
