
----
### Twitter Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 3505.75 | 1.20403 | 88.3489ms | 2821 | 2560 | 218555 | 767.4 | 5.49261 | -(Win) | false |
| simdjson (ondemand) | 2595.33 | 0.721264 | 101.841ms | 2821 | 2560 | 143104 | 1036.6 | 0.499136 | 2(Loss) | true |
