
----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5151.44 | 0.0801794 | 1197.16ms | 24579 | 4890 | 65088.8 | 4550.26 | 0.0893794 | 0.989479 | 2.97263 | 0.388626 | 0.000154179 | 1.05831e-05 | 2.93698e-06 | 1(Win) | true |
| Glaze | 3543.41 | 0.0782501 | 1406.17ms | 24579 | 4890 | 131028 | 6615.2 | 0.126761 | 1.43473 | 3.74088 | 0.481387 | 0.000380701 | 1.25799e-05 | 3.69411e-06 | 2(Loss) | true |
