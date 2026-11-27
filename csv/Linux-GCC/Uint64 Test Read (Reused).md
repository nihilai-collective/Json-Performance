
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1679.91 | 0.058977 | 71.1047ms | 1213 | 160 | 26.3898 | 688.612 | 0.0852438 | 1.41565 | 1(Win) | true |
| simdjson (reflection) | 1117.66 | 0.0446032 | 107.23ms | 1213 | 160 | 34.1 | 1035.03 | 0.221724 | 2.15809 | 2(Loss) | true |
| Glaze | 964.011 | 0.0953807 | 121.824ms | 1213 | 160 | 209.604 | 1199.99 | 0.0234321 | 2.49423 | 3(Loss) | true |
| simdjson (ondemand) | 315.636 | 0.0310484 | 368.7ms | 1213 | 40 | 51.7949 | 3665 | 0.00363815 | 7.78551 | 4(Loss) | true |
