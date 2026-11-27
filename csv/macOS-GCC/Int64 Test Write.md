
----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 247.446 | 0.521611 | 506.719ms | 1313 | 1280 | 891813 | 5060.4 | 1.26434 | 1(Win) | true |
| simdjson (reflection) | 233.484 | 0.483551 | 495.528ms | 1313 | 1280 | 860817 | 5363 | 3.27177 | 2(Loss) | true |
| Glaze | 161.105 | 0.59957 | 757.341ms | 1313 | 640 | 1.38986e+06 | 7772.4 | 0.99358 | 3(Loss) | true |
