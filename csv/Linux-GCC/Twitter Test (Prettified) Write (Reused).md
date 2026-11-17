
----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17726.5 | 0.377511 | 3940.12ms | 716365 | 80 | 1.69345e+06 | 38540 | 0.274285 | 0.139535 | 1(Win) | true |
| Glaze | 4839.05 | 0.0628528 | 7281.26ms | 716365 | 2560 | 2.01575e+07 | 141180 | 0.0335034 | 0.511523 | 2(Loss) | true |
| simdjson (reflection) | 564.448 | 0.218812 | 7595.68ms | 716365 | 320 | 2.24446e+09 | 1.21035e+06 | 0.479294 | 4.38613 | 3(Loss) | true |
