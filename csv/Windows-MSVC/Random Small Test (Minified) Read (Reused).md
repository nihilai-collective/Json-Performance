
----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1208.85 | 0.107055 | 497.889ms | 5094 | 2560 | 47383.3 | 4018.71 | 0.12165 | 2.50286 | 1(Win) | true |
| Jsonifier (two-stage) | 1034.14 | 0.101118 | 571.316ms | 5094 | 2560 | 57763 | 4697.62 | 0.340598 | 2.92691 | 2(Loss) | true |
| Glaze | 976.486 | 0.108409 | 590.816ms | 5094 | 160 | 4654.09 | 4975 | 0.100402 | 3.09954 | 3(Loss) | true |
| simdjson (ondemand) | 699.774 | 0.0803755 | 798.231ms | 5094 | 2560 | 79705.7 | 6942.27 | 0.142716 | 4.32839 | 4(Loss) | true |
