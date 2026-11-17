
----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1012.17 | 0.783595 | 518.411ms | 4604 | 160 | 184872 | 4337.94 | 0.287829 | 2.4307 | 1(Win) | true |
| Jsonifier (two-stage) | 900.229 | 0.0982716 | 559.629ms | 4604 | 30 | 689.195 | 4877.33 | 0.35752 | 2.73401 | 2(Loss) | true |
| Glaze | 782.973 | 0.0766035 | 642.386ms | 4604 | 80 | 1476.27 | 5607.75 | 0.0374622 | 3.14685 | 3(Loss) | true |
| simdjson (reflection) | 701.555 | 0.130684 | 710.087ms | 4604 | 4890 | 327116 | 6258.55 | 0.0348185 | 3.51393 | 4(Loss) | true |
| simdjson (ondemand) | 585.792 | 0.149237 | 840.947ms | 4604 | 4890 | 611850 | 7495.35 | 0.27499 | 4.21184 | 5(Loss) | true |
