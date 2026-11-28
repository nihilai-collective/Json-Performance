
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1524.07 | 1.96951 | 93.3842ms | 1313 | 640 | 167578 | 821.6 | 3.02172 | 1(Win) | true |
| Glaze | 886.307 | 1.99056 | 149.532ms | 1313 | 320 | 253081 | 1412.8 | 2.3175 | 2(Loss) | true |
| simdjson (reflection) | 782.596 | 0.557161 | 168.969ms | 1313 | 4890 | 388620 | 1600.03 | 2.43743 | 3(Loss) | true |
| simdjson (ondemand) | 263.327 | 2.17991 | 432.327ms | 1313 | 40 | 429807 | 4755.2 | 2.43566 | 4(Loss) | true |
