
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1471.52 | 0.328928 | 92.0675ms | 1313 | 320 | 2506.96 | 850.938 | 0.331614 | 2.02002 | 1(Win) | true |
| Glaze | 417.391 | 0.159821 | 325.244ms | 1313 | 30 | 689.655 | 3000 | 0.896861 | 7.15065 | 2(Loss) | true |
| simdjson (ondemand) | 368.422 | 0.110954 | 375.465ms | 1313 | 80 | 1137.66 | 3398.75 | 0.40293 | 8.17011 | 3(Loss) | true |
