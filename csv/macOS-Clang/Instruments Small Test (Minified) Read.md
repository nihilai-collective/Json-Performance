
----
### Instruments Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2782.89 | 0.147597 | 163.705ms | 4669 | 4890 | 27272.3 | 1600.03 | 0.0982064 | 1(Win) | true |
| Jsonifier (two-stage) | 1443 | 0.806927 | 291.409ms | 4669 | 1280 | 793587 | 3085.73 | 0.625898 | 2(Loss) | true |
| Glaze | 1357.3 | 0.11561 | 332.968ms | 4669 | 4890 | 70339.4 | 3280.56 | 0.115545 | 3(Loss) | true |
| simdjson (ondemand) | 624.805 | 0.111666 | 717.716ms | 4669 | 1280 | 81060.9 | 7126.55 | 0.128305 | 4(Loss) | true |
