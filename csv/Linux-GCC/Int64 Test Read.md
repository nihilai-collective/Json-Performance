
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 2547.5 | 0.0743738 | 52.1412ms | 1313 | 160 | 21.3827 | 491.531 | 0.054706 | 0.921416 | 1(Win) | true |
| simdjson (stage-1) | 1058.45 | 0.0544362 | 121.067ms | 1313 | 40 | 16.5891 | 1183.03 | 0.0345041 | 2.2885 | 2(Loss) | true |
