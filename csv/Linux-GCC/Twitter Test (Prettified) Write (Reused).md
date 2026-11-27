
----
### Twitter Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18630 | 0.117589 | 4429.99ms | 716365 | 2560 | 4.76008e+06 | 36670.9 | 0.229384 | 0.271341 | 0.750301 | 0.0920313 | 0.000175843 | 0.00353395 | 8.46068e-06 | 1(Win) | true |
| Glaze | 6470.63 | 0.199045 | 5769.93ms | 716365 | 640 | 2.82657e+07 | 105582 | 0.113434 | 0.780965 | 2.69622 | 0.435824 | 0.000330998 | 0.00260586 | 5.37872e-06 | 2(Loss) | true |
| simdjson (reflection) | 535.514 | 0.313069 | 8140.54ms | 716365 | 160 | 2.55227e+09 | 1.27574e+06 | 0.273247 | 9.3992 | 30.5378 | 6.83002 | 0.0700141 | 0.293109 | 0.00119039 | 3(Loss) | true |
