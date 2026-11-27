
----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 947.805 | 1.26351 | 5288.2ms | 53331 | 2560 | 1.17685e+09 | 53661.2 | 0.209358 | 3.2046 | 1(Win) | true |
| Glaze | 890.469 | 0.883151 | 5677.07ms | 53331 | 4890 | 1.24423e+09 | 57116.4 | 0.499437 | 3.41102 | 2(Loss) | true |
| Jsonifier (two-stage) | 867.888 | 0.638488 | 5861.83ms | 53331 | 4890 | 6.84615e+08 | 58602.5 | 0.292936 | 3.49857 | 3(Loss) | true |
| simdjson (ondemand) | 675.637 | 0.773778 | 7508.46ms | 53331 | 2560 | 8.68572e+08 | 75277.7 | 0.256219 | 4.49647 | 4(Loss) | true |
