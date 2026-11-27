
----
### Apache Builds Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1640.52 | 0.740851 | 9100.17ms | 124597 | 4890 | 1.40807e+09 | 72431.2 | 1.89576 | 1.85187 | 1(Win) | true |
| Jsonifier (two-stage) | 1450.92 | 0.711234 | 5236.51ms | 124597 | 2560 | 8.68544e+08 | 81896.2 | 0.877251 | 2.09398 | 2(Loss) | true |
| Glaze | 1390.3 | 0.897952 | 5470.9ms | 124597 | 1280 | 7.53899e+08 | 85467 | 0.0360024 | 2.18523 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1281.76 | 0.779436 | 5648.07ms | 124597 | 2560 | 1.3366e+09 | 92704.4 | 2.72942 | 2.37046 | -(Loss) | false |
