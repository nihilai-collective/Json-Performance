
----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 20950.7 | 0.0861785 | 8351.69ms | 1834197 | 1280 | 6.6268e+06 | 83492.6 | 0.0738087 | 0.118132 | 1(Win) | true |
| simdjson (stage-1) | 16371.2 | 0.0862216 | 5498.17ms | 1834197 | 640 | 5.43183e+06 | 106848 | 0.0555372 | 0.151185 | 2(Loss) | true |
