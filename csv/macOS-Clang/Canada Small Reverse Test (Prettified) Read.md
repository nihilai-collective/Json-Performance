
----
### Canada Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 989.403 | 0.151764 | 1148.44ms | 11579 | 640 | 183618 | 11160.9 | 0.180362 | 1(Win) | true |
| simdjson (ondemand) | 952.59 | 0.0423128 | 1177.03ms | 11579 | 80 | 1924.7 | 11592.2 | 0.0129381 | 2(Loss) | true |
