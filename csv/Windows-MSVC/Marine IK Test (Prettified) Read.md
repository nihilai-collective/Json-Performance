
----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 722.617 | 0.562276 | 6941.17ms | 7351818 | 40 | 1.19051e+11 | 9.70257e+06 | 0.0639759 | 3.42609 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 717.684 | 1.64784 | 6831.64ms | 7351818 | 30 | 7.77453e+11 | 9.76926e+06 | 1.30868 | 3.44963 | 1(Tie) | true |
