
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 749.477 | 0.636853 | 8291.78ms | 1834197 | 160 | 3.53487e+10 | 2.33393e+06 | 0.317869 | 3.30334 | 1(Win) | true |
| Jsonifier (two-stage) | 678.362 | 0.395793 | 9264.55ms | 1834197 | 30 | 3.12484e+09 | 2.5786e+06 | 0.233688 | 3.64963 | 2(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 227.945 | 0.171654 | 5725.47ms | 1834197 | 40 | 6.94061e+09 | 7.67388e+06 | 8.37346 | 10.8614 | -(Loss) | false |
| Glaze | 204.666 | 0.316303 | 6344.62ms | 1834197 | 30 | 2.19244e+10 | 8.54672e+06 | 0.0757611 | 12.0968 | 4(Loss) | true |
