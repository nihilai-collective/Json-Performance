
----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2420.58 | 0.585776 | 371.37ms | 9378 | 640 | 299795 | 3694.8 | 0.0108272 | 1(Win) | true |
| Jsonifier (two-stage) | 2214.54 | 0.129791 | 410.687ms | 9378 | 4890 | 134355 | 4038.57 | 0.25495 | 2(Loss) | true |
| simdjson (reflection) | 1806.23 | 0.192778 | 536.794ms | 9378 | 2560 | 233254 | 4951.5 | 0.832892 | 3(Loss) | true |
| Glaze | 1581.18 | 0.170333 | 572.169ms | 9378 | 4890 | 453902 | 5656.24 | 0.293697 | 4(Loss) | true |
| simdjson (ondemand) | 1359.04 | 0.669354 | 655.388ms | 9378 | 160 | 310448 | 6580.8 | 0.0729927 | 5(Loss) | true |
