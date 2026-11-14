
----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7346.46 | 0.473187 | 192.471ms | 14795 | 2560 | 211436 | 1920.6 | 0.528278 | 1(Win) | true |
| Glaze | 3688.21 | 0.84588 | 422.403ms | 14795 | 160 | 167547 | 3825.6 | 0.716091 | 2(Loss) | true |
| simdjson (reflection) | 261.832 | 1.11546 | 5106.89ms | 14795 | 80 | 2.89055e+07 | 53888 | 1.21409 | 3(Loss) | true |
