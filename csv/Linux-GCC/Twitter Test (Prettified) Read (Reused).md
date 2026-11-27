
----
### Twitter Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2733 | 0.0375586 | 7583.84ms | 360584 | 2560 | 5.71731e+06 | 125825 | 0.0492084 | 1.85679 | 6.75606 | 1.11904 | 0.00814505 | 4.01551e-05 | 7.07186e-06 | 1(Win) | true |
| simdjson (ondemand) | 2666.22 | 0.0501821 | 7803.75ms | 360584 | 1280 | 5.36204e+06 | 128977 | 0.151804 | 1.8987 | 7.20064 | 1.12994 | 0.00561431 | 9.96842e-05 | 7.69585e-06 | 2(Loss) | true |
