
----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4496.42 | 0.0712863 | 5067.82ms | 1834197 | 640 | 4.9221e+07 | 389026 | 0.153147 | 1.13485 | 5.76928 | 0.914887 | 0.00568679 | 0.0754833 | 1.30873e-05 | 1(Win) | true |
| simdjson (ondemand) | 4370.32 | 0.100148 | 5206.38ms | 1834197 | 160 | 2.57081e+07 | 400251 | 0.0513336 | 1.16334 | 6.52898 | 0.874439 | 0.00339968 | 0.0753867 | 3.85046e-06 | 2(Loss) | true |
