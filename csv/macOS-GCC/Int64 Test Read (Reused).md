
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1637.69 | 1.10918 | 80.4009ms | 1313 | 2560 | 184124 | 764.6 | 0.984201 | 1(Win) | true |
| Glaze | 915.868 | 1.72421 | 144.133ms | 1313 | 640 | 355653 | 1367.2 | 1.06446 | 2(Loss) | true |
| simdjson (reflection) | 775.052 | 1.20756 | 166.595ms | 1313 | 640 | 243593 | 1615.6 | 0.17301 | 3(Loss) | true |
| simdjson (ondemand) | 307.448 | 1.15091 | 404.066ms | 1313 | 320 | 703099 | 4072.8 | 0.295508 | 4(Loss) | true |
