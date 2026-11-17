
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1994.2 | 0.0452342 | 1324.57ms | 9578 | 2560 | 10989.8 | 4580.44 | 0.0357712 | 2.55286 | 13.4262 | 2.045 | 0.00195777 | 1.4315e-05 | 6.52537e-07 | 1(Win) | true |
| Jsonifier (generic) | 1794.85 | 0.0265037 | 1365.51ms | 9578 | 4890 | 8896.43 | 5089.17 | 0.0256442 | 2.85401 | 14.9756 | 2.40698 | 0.00169883 | 2.20982e-05 | 4.67585e-06 | 2(Loss) | true |
