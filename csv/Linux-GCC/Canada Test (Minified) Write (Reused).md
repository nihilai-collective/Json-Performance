
----
### Canada Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1825.55 | 0.0860629 | 6915.04ms | 2090326 | 160 | 1.41316e+08 | 1.09199e+06 | 0.714163 | 1.35615 | 1(Win) | true |
| Glaze | 1373.9 | 0.263705 | 9278.38ms | 2090234 | 30 | 4.39176e+08 | 1.45091e+06 | 0.635275 | 1.80199 | 2(Loss) | true |
| simdjson (reflection) | 1185.21 | 0.0920759 | 5244.17ms | 2090326 | 160 | 3.83749e+08 | 1.68197e+06 | 0.524064 | 2.08886 | 3(Loss) | true |
