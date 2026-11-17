
----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 966.681 | 0.0588951 | 6847.14ms | 461466 | 160 | 1.15025e+07 | 455257 | 0.215314 | 3.144 | 1(Win) | true |
| Jsonifier (two-stage) | 861.622 | 0.0566065 | 7551.63ms | 461466 | 40 | 3.34379e+06 | 510768 | 0.0226731 | 3.52743 | 2(Loss) | true |
| Glaze | 813.414 | 0.0449768 | 7914.87ms | 461466 | 160 | 9.47446e+06 | 541039 | 0.0332804 | 3.73647 | 3(Loss) | true |
| simdjson (ondemand) | 613.952 | 0.220627 | 5062.33ms | 461466 | 40 | 1.00043e+08 | 716812 | 0.0450111 | 4.9504 | 4(Loss) | true |
