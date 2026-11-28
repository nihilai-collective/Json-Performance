
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1968.41 | 0.077859 | 66.8416ms | 1313 | 320 | 78.4991 | 636.134 | 0.0378118 | 1.20712 | 1(Win) | true |
| simdjson (reflection) | 1111.4 | 0.0827746 | 120.53ms | 1313 | 30 | 26.092 | 1126.67 | 0.0354904 | 2.17157 | 2(Loss) | true |
| Glaze | 1006.16 | 0.0684327 | 127.748ms | 1313 | 80 | 58.0252 | 1244.51 | 0.331358 | 2.40732 | 3(Loss) | true |
| simdjson (ondemand) | 359.067 | 0.0299381 | 355.886ms | 1313 | 40 | 43.6 | 3487.3 | 0.190805 | 6.84933 | 4(Loss) | true |
