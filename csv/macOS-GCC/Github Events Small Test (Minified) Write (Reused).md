
----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE DID NOT CONVERGE | 11740.5 | 3.51879 | 18.7489ms | 1996 | 4890 | 159163 | 162.133 | 5.14483 | -(Tie) | false |
| simdjson (reflection) STATISTICAL TIE | 10754.4 | 6.04424 | 20.8809ms | 1996 | 1280 | 146501 | 177 | 1.72414 | 1(Tie) | true |
| Glaze | 3005.74 | 2.37701 | 65.5862ms | 1996 | 2560 | 580124 | 633.3 | 0.779758 | 3(Loss) | true |
