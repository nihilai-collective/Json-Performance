
----
### Random Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2534.3 | 0.0619629 | 6277.45ms | 461466 | 1280 | 1.48197e+07 | 173653 | 0.135307 | 1.98898 | 10.3841 | 1.97127 | 0.00485455 | 0.00412692 | 1.92373e-05 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1546.85 | 0.207041 | 9241.23ms | 461466 | 80 | 2.77578e+07 | 284506 | 0.179511 | 3.27363 | 15.4508 | 2.54139 | 0.0150416 | 0.0250327 | 1.70652e-05 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1543.7 | 0.0878065 | 9154.93ms | 461466 | 640 | 4.0104e+07 | 285087 | 0.0888736 | 3.26895 | 15.2034 | 2.89846 | 0.0107623 | 0.00890572 | 3.01282e-05 | 2(Tie) | true |
| simdjson (ondemand) | 1026.76 | 0.316341 | 6360.65ms | 461466 | 80 | 1.47077e+08 | 428619 | 0.245329 | 4.89061 | 21.4641 | 3.52344 | 0.00331666 | 0.0311601 | 4.17149e-05 | 4(Loss) | true |
