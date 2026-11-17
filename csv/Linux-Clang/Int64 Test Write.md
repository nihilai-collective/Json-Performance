
----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 934.881 | 0.0752055 | 1128.99ms | 3862 | 2560 | 22472.5 | 3939.63 | 0.189982 | 5.51928 | 26.4037 | 5.40963 | 0.00714939 | 0.000154854 | 8.44567e-05 | 1(Win) | true |
| Glaze | 882.093 | 0.184121 | 1146.14ms | 3862 | 320 | 18912.6 | 4175.4 | 0.258802 | 5.78433 | 29.5873 | 5.69575 | 0.00796786 | 1.942e-05 | 0 | 2(Loss) | true |
