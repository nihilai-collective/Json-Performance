
----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21807.4 | 0.321605 | 8181.81ms | 7351818 | 40 | 4.27648e+07 | 321508 | 0.110554 | 0.11352 | 1(Win) | true |
| simdjson (stage-1) | 19365.8 | 0.270111 | 9311.57ms | 7351818 | 1280 | 1.2241e+09 | 362043 | 0.122655 | 0.127835 | 2(Loss) | true |
