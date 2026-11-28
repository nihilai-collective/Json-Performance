
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1781.95 | 1.29865 | 78.751ms | 1313 | 2560 | 213189 | 702.7 | 2.29422 | 1(Win) | true |
| Glaze | 883.929 | 0.725042 | 141.395ms | 1313 | 2560 | 270060 | 1416.6 | 1.07021 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 788.089 | 0.47113 | 172.198ms | 1313 | 4890 | 274012 | 1588.88 | 5.20403 | -(Loss) | false |
| simdjson (ondemand) | 312.562 | 0.267492 | 428.634ms | 1313 | 4890 | 561551 | 4006.16 | 0.166631 | 4(Loss) | true |
