
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 939.938 | 0.134541 | 6585.58ms | 1834197 | 40 | 2.50764e+08 | 1.861e+06 | 0.455178 | 2.63399 | 1(Win) | true |
| Jsonifier (two-stage) | 811.688 | 0.0917692 | 7398.46ms | 1834197 | 80 | 3.12895e+08 | 2.15505e+06 | 1.10669 | 3.05017 | 2(Loss) | true |
| Glaze | 717.811 | 0.122035 | 8180.55ms | 1834197 | 160 | 1.41501e+09 | 2.43689e+06 | 0.425407 | 3.44908 | 3(Loss) | true |
| simdjson (reflection) | 680.137 | 0.0797522 | 8605.22ms | 1834197 | 160 | 6.73138e+08 | 2.57187e+06 | 0.0705947 | 3.64015 | 4(Loss) | true |
| simdjson (ondemand) | 605.768 | 0.0837196 | 9723.81ms | 1834197 | 160 | 9.35092e+08 | 2.88762e+06 | 0.39514 | 4.08706 | 5(Loss) | true |
