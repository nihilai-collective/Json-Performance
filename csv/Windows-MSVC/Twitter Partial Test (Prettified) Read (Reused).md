
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 9561.37 | 0.279867 | 6569.64ms | 631514 | 320 | 9.94445e+06 | 62988.8 | 0.358891 | 0.258792 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 9555.54 | 0.268867 | 6538.18ms | 631514 | 320 | 9.18926e+06 | 63027.2 | 0.0918105 | 0.258975 | 1(Tie) | true |
| simdjson (ondemand) | 5207.71 | 0.263474 | 6033.3ms | 631514 | 1280 | 1.18838e+08 | 115648 | 0.318721 | 0.475289 | 3(Loss) | true |
| Glaze | 3507.22 | 0.197822 | 9002.17ms | 631514 | 1280 | 1.47707e+08 | 171720 | 0.588195 | 0.705806 | 4(Loss) | true |
