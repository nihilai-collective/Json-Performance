
----
### Random Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1007.76 | 0.113527 | 516.63ms | 5094 | 160 | 4792.06 | 4820.62 | 0.14282 | 3.0066 | 1(Win) | true |
| Jsonifier (two-stage) | 832.922 | 0.197858 | 622.7ms | 5094 | 40 | 5326.92 | 5832.5 | 0.976231 | 3.62996 | 2(Loss) | true |
| Glaze | 679.205 | 0.240016 | 766.107ms | 5094 | 40 | 11788.5 | 7152.5 | 1.02401 | 4.45654 | 3(Loss) | true |
| simdjson (ondemand) | 533.546 | 0.817336 | 939.29ms | 5094 | 2560 | 1.4178e+07 | 9105.16 | 0.287406 | 5.68266 | 4(Loss) | true |
