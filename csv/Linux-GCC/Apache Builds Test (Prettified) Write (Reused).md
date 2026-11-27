
----
### Apache Builds Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 26608.6 | 0.300755 | 479.033ms | 136037 | 2560 | 550474 | 4875.68 | 0.447201 | 0.0925176 | 1(Win) | true |
| Glaze | 6292.42 | 0.186627 | 2055.29ms | 136076 | 2560 | 3.7924e+06 | 20623.6 | 0.174627 | 0.392939 | 2(Loss) | true |
| simdjson (reflection) | 605.457 | 0.417125 | 5507.55ms | 136037 | 40 | 3.1955e+07 | 214276 | 0.0598674 | 4.08845 | 3(Loss) | true |
