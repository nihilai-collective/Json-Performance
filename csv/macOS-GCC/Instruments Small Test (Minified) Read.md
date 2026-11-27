
----
### Instruments Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2754.19 | 0.639072 | 165.589ms | 4669 | 2560 | 273274 | 1616.7 | 0.424982 | 1(Win) | true |
| Jsonifier (two-stage) | 1685.67 | 0.397228 | 268.567ms | 4669 | 2560 | 281852 | 2641.5 | 0.208649 | 2(Loss) | true |
| Glaze | 1500.34 | 0.287682 | 323.612ms | 4669 | 1280 | 93304.9 | 2967.8 | 0.0336836 | 3(Loss) | true |
| simdjson (reflection) | 1342.47 | 0.437227 | 335.865ms | 4669 | 1280 | 269192 | 3316.8 | 0.278147 | 4(Loss) | true |
| simdjson (ondemand) | 1130.39 | 0.137568 | 399.227ms | 4669 | 4890 | 143595 | 3939.1 | 0.479982 | 5(Loss) | true |
