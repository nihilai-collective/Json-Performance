
----
### Apache Builds Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2273.88 | 0.0706804 | 3962.58ms | 94653 | 2560 | 2.01545e+06 | 39697.8 | 0.0433154 | 1.08807 | 1(Win) | true |
| simdjson (ondemand) | 1804.84 | 0.105709 | 4995.33ms | 94653 | 1280 | 3.57788e+06 | 50014.4 | 0.268509 | 1.37105 | 2(Loss) | true |
