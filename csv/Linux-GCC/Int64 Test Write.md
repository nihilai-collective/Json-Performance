
----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 366.564 | 0.0698951 | 1064.07ms | 1313 | 80 | 456.05 | 3415.97 | 0.0358481 | 14.4805 | 69.1927 | 15.0335 | 0.0175838 | 0.000180883 | 0 | 1(Win) | true |
| simdjson (reflection) | 365.617 | 0.0661576 | 1059.63ms | 1313 | 160 | 821.403 | 3424.82 | 0.194885 | 14.2555 | 68.9733 | 14.9185 | 0.0152371 | 0.000390327 | 8.09216e-05 | 2(Loss) | true |
| Glaze | 316.266 | 0.047672 | 1115.13ms | 1313 | 2560 | 9119.92 | 3959.25 | 0.377935 | 16.4438 | 77.4501 | 15.3869 | 0.0313181 | 0.000422161 | 0.000194569 | 3(Loss) | true |
