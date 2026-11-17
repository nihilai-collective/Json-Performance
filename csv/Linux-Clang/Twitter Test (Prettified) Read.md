
----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15969.1 | 0.0397243 | 4506.37ms | 631514 | 2560 | 574590 | 37714 | 0.13825 | 0.316257 | 1.73716 | 0.0785035 | 2.25259e-05 | 1.21793e-06 | 8.41232e-07 | 1(Win) | true |
| simdjson (stage-1) | 15173 | 0.0213538 | 4693.9ms | 631514 | 2560 | 183913 | 39692.9 | 0.028649 | 0.337355 | 1.59418 | 0.0666589 | 2.32032e-05 | 3.81647e-07 | 6.49481e-08 | 2(Loss) | true |
