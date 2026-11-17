
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1426.73 | 0.653823 | 6155.79ms | 5373214 | 80 | 4.4116e+10 | 3.59164e+06 | 0.239046 | 2.13013 | 1(Win) | true |
| Jsonifier | 1321.07 | 0.621342 | 6643.12ms | 5373214 | 30 | 1.7426e+10 | 3.87889e+06 | 0.602317 | 2.30053 | 2(Loss) | true |
| simdjson (ondemand) | 939.727 | 0.123664 | 9008.72ms | 5373214 | 40 | 1.81891e+09 | 5.45296e+06 | 0.234185 | 3.23395 | 3(Loss) | true |
| Glaze | 827.318 | 0.398433 | 9969.19ms | 5373214 | 80 | 4.87218e+10 | 6.19386e+06 | 0.888597 | 3.67371 | 4(Loss) | true |
