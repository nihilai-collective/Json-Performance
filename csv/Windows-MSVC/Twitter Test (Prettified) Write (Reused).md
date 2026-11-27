
----
### Twitter Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10564.2 | 0.180795 | 6623.84ms | 716365 | 640 | 8.74883e+06 | 64669.4 | 0.419127 | 0.23424 | 1(Win) | true |
| Glaze | 4924.92 | 0.130771 | 7268.11ms | 716365 | 1280 | 4.21212e+07 | 138719 | 0.128243 | 0.502572 | 2(Loss) | true |
