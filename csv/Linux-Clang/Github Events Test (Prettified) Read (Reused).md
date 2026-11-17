
----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1793.93 | 0.0411185 | 4733.23ms | 65103 | 1280 | 259225 | 34609.6 | 0.0271618 | 2.8706 | 10.2017 | 1.90724 | 0.00869648 | 8.88016e-06 | 2.70005e-06 | 1(Win) | true |
| simdjson (ondemand) | 1421.04 | 0.0305932 | 5708.22ms | 65103 | 2560 | 457383 | 43691.3 | 0.098186 | 3.62497 | 13.8407 | 2.45858 | 0.0148727 | 1.08542e-05 | 2.14804e-06 | 2(Loss) | true |
