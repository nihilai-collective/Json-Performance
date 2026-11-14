
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1637.3 | 0.0479444 | 939.292ms | 3862 | 2560 | 2977.71 | 2249.49 | 0.0773362 | 3.20839 | 16.4606 | 1.99171 | 0.00062589 | 4.88534e-05 | 1.43627e-05 | 1(Win) | true |
| simdjson (ondemand) | 806.508 | 0.0239865 | 1168.63ms | 3862 | 4890 | 5867.45 | 4566.71 | 0.00173734 | 6.43958 | 27.7962 | 3.39203 | 0.0164342 | 3.53187e-05 | 3.70661e-06 | 2(Loss) | true |
