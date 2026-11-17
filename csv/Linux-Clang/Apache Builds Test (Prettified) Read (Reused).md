
----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2569.59 | 0.0249159 | 6605.71ms | 124597 | 2560 | 339845 | 46242.8 | 0.062905 | 1.97224 | 8.87835 | 1.58957 | 0.00465028 | 1.71114e-05 | 1.28195e-05 | 1(Win) | true |
| simdjson (ondemand) | 2108.02 | 0.0354263 | 7664.66ms | 124597 | 1280 | 510422 | 56368.2 | 0.024264 | 2.42511 | 9.99071 | 1.71305 | 0.00787908 | 5.28579e-06 | 2.28863e-06 | 2(Loss) | true |
