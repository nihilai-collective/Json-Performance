
----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2018.17 | 0.066521 | 8823.33ms | 631514 | 1280 | 5.04401e+07 | 298418 | 0.494217 | 1.22659 | 1(Win) | true |
| simdjson (ondemand) | 1791.48 | 0.335779 | 9630.98ms | 631514 | 30 | 3.82272e+07 | 336180 | 0.23839 | 1.38185 | 2(Loss) | true |
| Jsonifier STATISTICAL TIE | 1662.79 | 0.16706 | 5126.62ms | 631514 | 640 | 2.34326e+08 | 362198 | 0.185497 | 1.4888 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 1662.78 | 0.273509 | 5264.84ms | 631514 | 80 | 7.85109e+07 | 362200 | 0.197102 | 1.48881 | 3(Tie) | true |
