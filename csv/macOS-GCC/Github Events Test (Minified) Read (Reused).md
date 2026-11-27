
----
### Github Events Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2314.11 | 0.192291 | 2903.59ms | 53331 | 320 | 571560 | 21978.4 | 0.0254861 | 1(Win) | true |
| Glaze | 1895.74 | 0.993866 | 3443.46ms | 53331 | 40 | 2.84393e+06 | 26828.8 | 0.575816 | 2(Loss) | true |
| Jsonifier (two-stage) | 1708.38 | 0.946323 | 3790.59ms | 53331 | 160 | 1.26996e+07 | 29771.2 | 0.861882 | 3(Loss) | true |
| simdjson (reflection) | 1321.61 | 0.427968 | 4601.65ms | 53331 | 1280 | 3.47203e+07 | 38483.6 | 1.08005 | 4(Loss) | true |
| simdjson (ondemand) | 1089.33 | 0.779257 | 5828.66ms | 53331 | 320 | 4.23596e+07 | 46689.6 | 0.263176 | 5(Loss) | true |
