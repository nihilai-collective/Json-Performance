
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2419.43 | 0.224773 | 622.165ms | 9578 | 640 | 46088.2 | 3775.39 | 0.0209045 | 1(Win) | true |
| Glaze | 1840.66 | 0.0839779 | 716.081ms | 9578 | 30 | 521.017 | 4962.5 | 0.028875 | 2(Loss) | true |
| simdjson (ondemand) | 1226.31 | 0.0515303 | 1006.7ms | 9578 | 30 | 441.972 | 7448.6 | 0.0376051 | 3(Loss) | true |
| Jsonifier (two-stage) | 975.195 | 0.125103 | 1189.35ms | 9578 | 30 | 4119.27 | 9366.63 | 0.0437916 | 4(Loss) | true |
