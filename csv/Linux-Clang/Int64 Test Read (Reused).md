
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2756 | 0.065219 | 136.671ms | 3862 | 80 | 60.772 | 1336.39 | 0.00841751 | 0.879541 | 1(Win) | true |
| Glaze | 1379.43 | 0.0611608 | 285.566ms | 3862 | 30 | 80 | 2670 | 0.024975 | 1.77642 | 2(Loss) | true |
| Jsonifier (two-stage) | 849.013 | 0.156082 | 437.726ms | 3862 | 4890 | 224188 | 4338.09 | 0.0362681 | 2.89687 | 3(Loss) | true |
| simdjson (ondemand) | 661.902 | 0.0341032 | 568.688ms | 3862 | 40 | 144.041 | 5564.4 | 0.197892 | 3.72192 | 4(Loss) | true |
