
----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 689.822 | 0.173843 | 822.165ms | 4604 | 40 | 4897.44 | 6365 | 0.0261917 | 3.57258 | 1(Win) | true |
| Jsonifier (two-stage) | 601.677 | 0.17359 | 887.501ms | 4604 | 4890 | 784698 | 7297.46 | 0.168821 | 4.10014 | 2(Loss) | true |
| simdjson (ondemand) | 213.65 | 0.2842 | 2283.62ms | 4604 | 320 | 1.0916e+06 | 20550.9 | 0.331909 | 11.5736 | 3(Loss) | true |
| Glaze | 181.94 | 0.120414 | 2603.59ms | 4604 | 4890 | 4.12929e+06 | 24132.8 | 0.0903496 | 13.5933 | 4(Loss) | true |
