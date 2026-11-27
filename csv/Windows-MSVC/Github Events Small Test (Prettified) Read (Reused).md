
----
### Github Events Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1843.7 | 0.37183 | 147.369ms | 2158 | 80 | 1378.16 | 1116.25 | 1.43488 | 1.62188 | 1(Win) | true |
| Glaze | 1776.02 | 0.134959 | 141.828ms | 2158 | 2560 | 6261.14 | 1158.79 | 0.673006 | 1.68263 | 2(Loss) | true |
| Jsonifier (two-stage) | 1601.58 | 0.525005 | 156.484ms | 2158 | 40 | 1820.51 | 1285 | 0.12987 | 1.85883 | 3(Loss) | true |
| simdjson (ondemand) | 1073 | 0.607605 | 235.763ms | 2158 | 2560 | 347683 | 1918.01 | 0.40283 | 2.80263 | 4(Loss) | true |
