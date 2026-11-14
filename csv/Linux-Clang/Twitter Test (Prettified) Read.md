
----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16009.5 | 0.0605804 | 4503.15ms | 631514 | 1280 | 664788 | 37618.8 | 0.0632533 | 0.316192 | 1.73716 | 0.0785035 | 2.53038e-05 | 2.69565e-06 | 2.2837e-06 | 1(Win) | true |
| simdjson (stage-1) | 15215.4 | 0.0375037 | 4689.62ms | 631514 | 2560 | 564143 | 39582.2 | 0.0949827 | 0.337967 | 1.59418 | 0.0666589 | 2.14471e-05 | 6.35996e-06 | 5.70492e-06 | 2(Loss) | true |
