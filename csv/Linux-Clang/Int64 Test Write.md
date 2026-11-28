
----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 327.786 | 0.242852 | 387.847ms | 1313 | 1280 | 110165 | 3820.1 | 0.0602237 | 7.50004 | 1(Win) | true |
| Glaze | 273.714 | 0.490795 | 467.209ms | 1313 | 320 | 161318 | 4574.75 | 0.307335 | 8.99017 | 2(Loss) | true |
